# http://sourceware.org/gdb/wiki/FAQ: to disable the
# "---Type <return> to continue, or q <return> to quit---"
# in batch mode:
set width 0
set height 0
set verbose off

# Events
-- Master
b src/test/kalray.c:79  # After recieve the first signal
-- Slave
b src/test/kalray.c:103 # Before send the first signal