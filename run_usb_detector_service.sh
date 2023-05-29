clear&&g++ -o usb_detector usb_detector.cpp -ludev&&sudo systemctl stop usb_detector&&sudo systemctl daemon-reload&&sudo systemctl start usb_detector&&sudo systemctl enable usb_detector
