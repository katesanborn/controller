#!/bin/bash

echo "=========================="
echo "Stopping App controller"

systemctl stop rosnodeChecker
systemctl stop controller
