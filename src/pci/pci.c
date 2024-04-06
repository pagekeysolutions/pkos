#include "pci.h"

#define CONFIG_ADDRESS_PORT 0xCF8
#define CONFIG_DATA_PORT 0xCFC

u32 read_pci_port(u8 bus, u8 slot, u8 function, u8 offset) {
    u32 address = 0;
    
    // Clear out any bits not within range
    function &= 0b111; // 3 bits
    
    // Set the bits
    address |= 0x80000000; // bit 31: enable = 1
    // bits 30-24: reserved, leave them as 0
    address |= (bus << 16); // bits 23-16: bus
    address |= (slot << 11); // bits 15-11: device/slot
    address |= (function << 8); // bits 10-8: function
    address |= offset; // bits 7-0: offset

    // Set the address to read
    outl(CONFIG_ADDRESS_PORT, address);

    // Read data from PCI
    return inl(CONFIG_DATA_PORT);
}

struct PCI_Device get_pci_device(u8 bus, u8 slot, u8 function) {
    struct PCI_Device device;
    u32 pci_data = read_pci_port(bus, slot, function, 0);
    device.vendor_id = pci_data & 0xffff;
    device.device_id = (pci_data >> 16) & 0xffff;
    pci_data = read_pci_port(bus, slot, function, 0x04);
    device.command = pci_data & 0xffff;
    device.status = (pci_data >> 16) & 0xffff;
    pci_data = read_pci_port(bus, slot, function, 0x09);
    device.base_class = (pci_data >> 16) & 0xff;
    device.sub_class = (pci_data >> 8) & 0xff;
    device.prog_interface = pci_data & 0xff;
    return device;
}

void lspci() {
    for (u8 i = 0; i < 255; i++) {
        for (u8 j = 0; j < 255; j++) {
            for (u8 k = 0; k < 8; k++) {
                struct PCI_Device device = get_pci_device(i, j, k);
                if (device.vendor_id == 0xFFFF) {
                    continue;
                }
                print("Bus ");
                print(itoa(i));
                print(" Device ");
                print(itoa(j));
                print(" Function ");
                print(itoa(k));
                print(": Vendor=");
                print(itoah(device.vendor_id));
                print(" Device=");
                print(itoah(device.device_id));
                print(" Class=");
                print(itoah(device.base_class));
                print(" SubClass=");
                print(itoah(device.sub_class));
                print(" ProgIf=");
                println(itoah(device.prog_interface));
            }
        }
    }
}


#define IDE_MASTER_COMMAND 0x1F0
#define IDE_MASTER_STATUS 0x1F2

// Source: https://forum.osdev.org/viewtopic.php?f=1&t=21151
// State (ready?)
#define    ATA_SR_BSY      0x80
#define    ATA_SR_DRDY      0x40
#define    ATA_SR_DF      0x20
#define    ATA_SR_DSC      0x10
#define    ATA_SR_DRQ      0x08
#define    ATA_SR_CORR      0x04
#define    ATA_SR_IDX      0x02
#define    ATA_SR_ERR      0x01
// Error states
#define    ATA_ER_BBK      0x80
#define    ATA_ER_UNC      0x40
#define    ATA_ER_MC      0x20
#define    ATA_ER_IDNF      0x10
#define    ATA_ER_MCR      0x08
#define    ATA_ER_ABRT      0x04
#define    ATA_ER_TK0NF   0x02
#define    ATA_ER_AMNF      0x01
// Commands
#define      ATA_CMD_READ_PIO         0x20
#define      ATA_CMD_READ_PIO_EXT      0x24
#define      ATA_CMD_READ_DMA         0xC8
#define      ATA_CMD_READ_DMA_EXT      0x25
#define      ATA_CMD_WRITE_PIO         0x30
#define      ATA_CMD_WRITE_PIO_EXT      0x34
#define      ATA_CMD_WRITE_DMA         0xCA
#define      ATA_CMD_WRITE_DMA_EXT      0x35
#define      ATA_CMD_CACHE_FLUSH      0xE7
#define      ATA_CMD_CACHE_FLUSH_EXT   0xEA
#define      ATA_CMD_PACKET            0xA0
#define       ATA_CMD_IDENTIFY_PACKET      0xA1
#define       ATA_CMD_IDENTIFY         0xEC
// Reading the identification space
#define    ATA_IDENT_DEVICETYPE   0
#define    ATA_IDENT_CYLINDERS   2
#define    ATA_IDENT_HEADS      6
#define    ATA_IDENT_SECTORS      12
#define    ATA_IDENT_SERIAL   20
#define    ATA_IDENT_MODEL      54
#define    ATA_IDENT_CAPABILITIES   98
#define    ATA_IDENT_FIELDVALID   106
#define    ATA_IDENT_MAX_LBA   120
#define   ATA_IDENT_COMMANDSETS   164
#define    ATA_IDENT_MAX_LBA_EXT   200
// Task file
#define      ATA_REG_DATA      0x00
#define      ATA_REG_ERROR      0x01
#define      ATA_REG_FEATURES   0x01
#define      ATA_REG_SECCOUNT0   0x02
#define      ATA_REG_LBA0      0x03
#define      ATA_REG_LBA1      0x04
#define      ATA_REG_LBA2      0x05
#define      ATA_REG_HDDEVSEL   0x06
#define      ATA_REG_COMMAND      0x07
#define      ATA_REG_STATUS      0x07
#define      ATA_REG_SECCOUNT1   0x08
#define      ATA_REG_LBA3      0x09
#define      ATA_REG_LBA4      0x0A
#define      ATA_REG_LBA5      0x0B
#define      ATA_REG_CONTROL      0x0C
#define      ATA_REG_ALTSTATUS   0x0C
#define      ATA_REG_DEVADDRESS   0x0D
// End copied code

void idetest() {
    struct PCI_Device ide_device = get_pci_device(0,1,1); // hard coded based on lspci output
    println("Hello world");
    print("prog iface: 0b");
    println(itoab(ide_device.prog_interface));
    print("command: 0x");
    println(itoah(ide_device.command));
    print("status: 0x");
    println(itoah(ide_device.status));
    print("iface: 0x");
    println(itoah(ide_device.prog_interface));

    // Let's try reading the status
    u8 status = ioport_in(IDE_MASTER_STATUS);
    print("IDE Master Status: 0x");
    println(itoah(status));

    // Okay, now send a read DMA command just for fun
    ioport_out(IDE_MASTER_COMMAND, 0xC8);

    terrible_sleep_impl(1000);
    
    status = ioport_in(IDE_MASTER_STATUS);
    print("IDE Master Status: 0x");
    println(itoah(status));
}
