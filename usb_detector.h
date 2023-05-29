#include <libudev.h>
#include <sys/select.h>
#include <utility>
class USB_Detector {
	private:
		struct udev* udev;
		struct udev_monitor* monitor;
		struct udev_device* dev;
		int fd;
		fd_set fds;
	public:
		void printDeviceInfo();
		USB_Detector();
		std::pair<int, udev_device*> detect();
		void teardown();
};
