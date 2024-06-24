#include <kernel.h>

uint16_t ata_base = 0;
uint8_t ata_type = 0;
char ata_name[40];

void ata_400ns()
{
	for (uint8_t i = 0; i < 4; i++)
		inb(ata_base + 7); // 400ns delay
}

uint8_t ata_poll()
{
	ata_400ns();

	uint8_t status = 0;
	for (;;) {
		status = inb(ata_base + 7);
		if (!(status & 0x80))
			break;
		if (status & 0x08)
			break;
		else if (status & 0x01)
			return ATA_DISK_ERR;
	}

	return ATA_OKAY;
}

uint8_t ata_identify(uint16_t ata, uint8_t type)
{
	ata_base = ata;
	ata_type = type;

	// Select disk
	outb(ata + 6, type); // master or slave
	for (uint16_t i = 0x1F2; i != 0x1F5; i++)
		outb(i, 0);
	outb(ata + 7, ATA_IDENTIFY);

	uint8_t status = inb(ata + 7);
	if (status == 0)
		return ATA_DISK_NOT_IDENTIFIED;

	if (ata_poll() != ATA_OKAY)
		return ATA_DISK_ERR;

	uint8_t buf[512];
	ata_read(0, buf, 1);

	for (uint8_t i = 0; i < 40; i += 2) {
		ata_name[i] = buf[54 + i + 1];
		ata_name[i + 1] = buf[54 + i];
	}

	ata_400ns();

	return ATA_OKAY;
}

uint8_t ata_read(uint32_t lba, uint8_t *buffer, uint32_t sector_count)
{
	outb(ata_base + 6, (ata_type == ATA_MASTER ? 0xE0 : 0xF0) |
						   ((lba >> 24) & 0x0F)); // Set master/slave
	outb(ata_base + 1, ATA_WAIT); // Send wait
	outb(ata_base + 2, sector_count); // Sector count
	outb(ata_base + 3, (uint8_t)lba); // Start sending LBA
	outb(ata_base + 4, (uint8_t)(lba >> 8));
	outb(ata_base + 5, (uint8_t)(lba >> 16)); // 24-bit LBA addressing
	outb(ata_base + 7, ATA_READ);

	uint16_t val = 0;
	uint32_t i = 0;

	for (; i < sector_count * 512; i += 2) {
		if (ata_poll() != ATA_OKAY)
			return ATA_DISK_ERR;
		val = inw(ata_base);
		buffer[i] = val & 0x00ff;
		if (i + 1 < sector_count * 512)
			buffer[i + 1] = (val >> 8) & 0x00ff;
	}

	ata_400ns();

	return ATA_OKAY;
}

uint8_t ata_write(uint32_t lba, uint8_t *buffer, uint32_t sector_count)
{
	outb(ata_base + 6,
		 (ata_type == ATA_MASTER ? 0xE0 : 0xF0) | ((lba >> 24) & 0x0F));
	outb(ata_base + 1, ATA_WAIT);
	outb(ata_base + 2, sector_count);
	outb(ata_base + 3, (uint8_t)lba);
	outb(ata_base + 4, (uint8_t)(lba >> 8));
	outb(ata_base + 5, (uint8_t)(lba >> 16));
	outb(ata_base + 7, ATA_WRITE);

	uint16_t val = 0;
	uint32_t i = 0;

	for (; i < sector_count * 512; i += 2) {
		if (ata_poll() != ATA_OKAY)
			return ATA_DISK_ERR;
		val = buffer[i];
		if (i + 1 < sector_count * 512)
			val |= ((uint16_t)buffer[i + 1] << 8);
		outw(ata_base, val);
	}

	ata_400ns();

	return ATA_OKAY;
}

int init_ata()
{
	uint8_t ata_status = ata_identify(ATA_PRIMARY, ATA_MASTER);
	return ata_status;
}