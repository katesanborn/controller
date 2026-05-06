#!/bin/bash

echo "=========================="
echo "Starting App controller for controller"


systemctl start controller
systemctl start rosnodeChecker
