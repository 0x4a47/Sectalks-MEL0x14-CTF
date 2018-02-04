#!/bin/bash
socat TCP-LISTEN:8887,reuseaddr,fork EXEC:"./stackme",pty
