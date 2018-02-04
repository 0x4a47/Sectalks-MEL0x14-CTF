#!/bin/bash
socat TCP-LISTEN:8891,reuseaddr,fork EXEC:"./simplywild",pty
