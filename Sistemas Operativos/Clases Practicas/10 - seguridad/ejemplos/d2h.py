#! /usr/bin/env python

import sys

sys.stdout.write("{:#08x}".format(int(sys.argv[1], 10)))