#!/bin/bash
socat TCP-LISTEN:8889,reuseaddr,fork EXEC:"./nopnopnop",pty
