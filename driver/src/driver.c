#include <stdio.h>
#include <usb.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define DATA_SIZE 16


void driver_init(void)
{               
	usb_init();                    //Initialisation de la librairie (par example determine le chemin du repertoire des bus et peripheriques)
	usb_find_busses();             // Enumère tous les bus USB du systemes
	usb_find_devices();            // Enumère tous les peripheriques sur tous les Bus présents)
}

struct usb_device *usb_find_My_device(int idV, int idP)
{  // recherche du device avec l'id Vendor et product
	struct usb_bus *busses;
	struct usb_bus *bus;
	struct usb_device *dev,*fdev;
	for (bus = usb_busses; bus; bus = bus->next)  // Parcours tous les bus USB
		for (dev = bus->devices; dev; dev = dev->next)    // Pour chaque bus, parcours tous les appareils branchés
			if ((dev->descriptor.idVendor == idV) && (dev->descriptor.idProduct ==idP ))  // on vérifie si les coordonnées (id vendeur; id produit) de notre appareil corespond
				return(dev);
	return(0);
}

void unlinkKernelDriver(usb_dev_handle *hdl)
{ // fonction pour détacher le driver du kernel (usbhid)
	char str[100];
	memset(&str[0], 0, 100); // réinitialisation de la variable 
	usb_get_driver_np(hdl, 0, &str[0], 100) >=0;  // récupération du driver lié à l'appareil
	if (strlen(str)>0) usb_detach_kernel_driver_np(hdl,0);
}


int readDevice(usb_dev_handle *hdl, int timeOut)
{
	unsigned char data[DATA_SIZE];
	int len;
	int i;
	
	printf("Reading data from device\n\t");

	usb_resetep(hdl, 0x081);
	
	len = usb_interrupt_read(hdl, 0x081, data, DATA_SIZE, timeOut);
	if (len >=0) {
		for(i=0; i<len; i++) printf("%02X ", data[i]);
		printf("\n");
	} else {
		printf("No data read\n");
	}
	
	return 0;
}


int writeDevice(usb_dev_handle *hdl, int timeOut, unsigned char* data, int len)
{
	int writeLen;
	int i;
	
	printf("Writing data to device\n\t");
	for(i=0; i<len; i++) printf("%02X ", data[i]);
	printf("\n");
	
	usb_resetep(hdl, 0x001);
	
	writeLen = usb_interrupt_write(hdl, 0x001, data, len, timeOut);
	if (writeLen >=0) {
		printf("%d bytes written\n", writeLen);
	} else {
		printf("No data written\n");
	}
	
	return 0;
}

int main (int argc, char * argv[])
{
	unsigned char data[DATA_SIZE] = { 0xAA, 0xAA, 0xAA, 0xAA, 
							          0xAA, 0xAA, 0xAA, 0xAA, 
							          0xAA, 0xAA, 0xAA, 0xAA, 
							          0xAA, 0xAA, 0xAA, 0xAA};

	if (getuid() >0) {
		printf("Warning ! you must launch this programme as root !\n\n");
		return 0;
	}

	int timeout = 0;


	printf("Driver device 18F4550\n05/2013 - C. MEICHEL\n\n");


	// *************  Initialise les devices *************
	driver_init();

	// *************  Recherche du device *************
	struct usb_device *myDevice = usb_find_My_device(0x04D8, 0x4541);  // on recherche l'appareil 04D8:4541
	if (!myDevice) {  // si on ne l'a pas trouvé ...
		printf("       ! No device found !\n");
		return 0;
	}
	printf("Device Ffound\n");

	usb_dev_handle *myDeviceHandle = usb_open(myDevice);  // ouverture du device
	if (!myDeviceHandle) {
		printf("       ! Could not open the device !\n");
		return 0;
	}
	printf("Device is open\n");
	
	unlinkKernelDriver(myDeviceHandle); // on détache le driver du Kernel (usbhid)
	usb_reset(myDeviceHandle);
	printf("Device is ready\n");

	//readDevice(myDeviceHandle, timeout);
	writeDevice(myDeviceHandle, timeout, data, DATA_SIZE);

	usb_reset(myDeviceHandle);
	usb_close(myDeviceHandle);
	
	return 0;
} 
