# http://sourceware.org/gdb/wiki/FAQ: to disable the
# "---Type <return> to continue, or q <return> to quit---"
# in batch mode:
set width 0
set height 0
set verbose off

# Nanvix interrupt
-- Master
b src/test/kalray.c:177 # After recieve the first signal
-- Slave
b src/test/kalray.c:207 # Before send the first signal