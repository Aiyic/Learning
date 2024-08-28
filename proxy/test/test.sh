#!/usr/bin/bash


# 获取当前时间
# start_time=$(date +"%Y-%m-%d %H:%M:%S")

for i in {1..3}; do
    (echo 'test'; sleep 300) | telnet 127.0.0.1 12345 &
    pid=$!
    pidArr+=($pid)
done


# for pid in ${pidArr[@]}; do
#     echo "$pid"
#     wait $pid
#     # kill -9 $pid
# done

# # 获取结束时间
# end_time=$(date +"%Y-%m-%d %H:%M:%S")

# # 计算耗时
# elapsed_time=$(( $(date -d "$end_time" +%s) - $(date -d "$start_time" +%s) ))
# echo "Elapsed time: $elapsed_time seconds"