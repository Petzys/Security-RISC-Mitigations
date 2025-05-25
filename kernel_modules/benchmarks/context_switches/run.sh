#!/bin/bash
sudo perf stat -o ../context_switches.stat stress-ng --switch 8 --timeout 60s --metrics --log-file ../context_switches.log