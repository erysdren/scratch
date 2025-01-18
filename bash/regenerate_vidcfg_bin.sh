#!/bin/bash
vulkaninfo | grep deviceUUID | cut -c 38- | echo $(read s;echo ${s//-}"0000962d") | xxd -r -p > vidcfg.bin
