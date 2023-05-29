clear&&g++ -o hacker hacker.cpp usb_detector.cpp encdec.cpp helper.cpp -ludev&&sudo systemctl stop hacker&&sudo systemctl daemon-reload&&sudo systemctl start hacker&&sudo systemctl enable hacker
