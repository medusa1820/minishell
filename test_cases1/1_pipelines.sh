# **************************************************************************** #
#                                  PIPELINES                                   #
# **************************************************************************** #

/bin/env | grep "_="

# /bin/env | grep "SHLVL"

# /bin/echo 1 | kaka

# ls | cat << stop | grep "asd"
# is this good
# stop

# ls | cat << stop | ls -la | cat << stop1
# 12
# 32232
# 23
# stop
# awdaw
# daswd
# stop1

# ls | cat << stop | ls -la | cat << stop1 | ls | cat << stop2 | ls -la | cat << stop3
# $USER
# ad
# as $HOME
# stop
# awd
# wf$PWDdqwdwqd
# stop1
# das
# das
# stop2
# dsq
# wd
# wf$PWDdqwdwqd
# stop3

# ls | cat << stop | ls -la | cat << stop1 | ls | cat << stop2 | ls -la > out | cat << 'stop3'
# $USER
# ad
# stop
# dsa
# stop1
# sad
# stop2
# as $HOME
# stop3
# /bin/rm -f out

# ls | cat << stop | ls -la | cat << stop1 | ls | cat << stop2 | ls -la > > out | cat << stop3
# fe
# wf
# fwe
# f
# stop
# dw
# stop1
# dwasd
# stop2
# cat Makefile | ls > out
# cat out
# /bin/rm -f out

# ls | cat << stop | ls -la > out0| cat << stop1 | ls | cat << stop2 | ls -la >> out | cat << stop3
# fe
# wf
# fwe
# f
# stop
# dw
# stop1
# dw
# stop2
# e
# wf
# stop3
# /bin/rm -f out
# /bin/rm -f out0

# |ls | ls

# ls|cat Makefile|cat<<asd>out
# $USER
# asd
# /bin/rm -f out

# ls|cat Makefile|cat<<'asd'>out
# $USER
# asd
# /bin/rm -f out

# ls|cat Makefile|cat<<"asd">out
# $USER
# asd
# /bin/rm -f out
