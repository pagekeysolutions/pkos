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
