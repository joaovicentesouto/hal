# http://sourceware.org/gdb/wiki/FAQ: to disable the
# "---Type <return> to continue, or q <return> to quit---"
# in batch mode:
set width 0
set height 0
set verbose off

# bsp interrupt
-- Master
b src/test/kalray.c:295 # After recieve the first signal
-- Slave
b src/test/kalray.c:325 # Before send the first signal