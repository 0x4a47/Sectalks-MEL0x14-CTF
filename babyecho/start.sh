#!/bin/bash
socat TCP-LISTEN:8888,reuseaddr,fork EXEC:"./babyecho",pty
