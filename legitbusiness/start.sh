#!/bin/bash
socat TCP-LISTEN:8890,reuseaddr,fork EXEC:"./legitbusiness",pty
