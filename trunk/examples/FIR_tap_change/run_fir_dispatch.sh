SPROFCOMMAND='sprofilev5'

#BLOCKSIZE=( 1024 2048 10240 20480 30720 40960 65536 131072 262144 524288)

DISPATCHSIZE=( 16 32 64 128 192 256 320 512 768 1024)

#rm op_log
#rm arg_list

NOBLOCKS=10240
TAPCHANGE=10
TAPCHANGEINTERVAL=10240

BLOCKSIZE=2560
for i in "${DISPATCHSIZE[@]}"
do
        SPROFFILENAME="sprofv5_"$NOBLOCKS"_"$BLOCKSIZE"_"$i"_"$TAPCHANGE"_"$TAPCHANGEINTERVAL".csv"
        echo 'run '$SPROFFILENAME
        echo $SPROFFILENAME >> arg_list_$BLOCKSIZE
        $SPROFCOMMAND -o $SPROFFILENAME -w ./ ./bin/amd/fir_tap_change $NOBLOCKS $BLOCKSIZE $i $TAPCHANGE $TAPCHANGEINTERVAL | grep "elapsedTime" >> op_log_$BLOCKSIZE
done


BLOCKSIZE=2048
for i in "${DISPATCHSIZE[@]}"
do
        SPROFFILENAME="sprofv5_"$NOBLOCKS"_"$BLOCKSIZE"_"$i"_"$TAPCHANGE"_"$TAPCHANGEINTERVAL".csv"
        echo 'run '$SPROFFILENAME
        echo $SPROFFILENAME >> arg_list_$BLOCKSIZE
        $SPROFCOMMAND -o $SPROFFILENAME -w ./ ./bin/amd/fir_tap_change $NOBLOCKS $BLOCKSIZE $i $TAPCHANGE $TAPCHANGEINTERVAL | grep "elapsedTime" >> op_log_$BLOCKSIZE
done



BLOCKSIZE=1024
for i in "${DISPATCHSIZE[@]}"
do
        SPROFFILENAME="sprofv5_"$NOBLOCKS"_"$BLOCKSIZE"_"$i"_"$TAPCHANGE"_"$TAPCHANGEINTERVAL".csv"
        echo 'run '$SPROFFILENAME
        echo $SPROFFILENAME >> arg_list_$BLOCKSIZE
        $SPROFCOMMAND -o $SPROFFILENAME -w ./ ./bin/amd/fir_tap_change $NOBLOCKS $BLOCKSIZE $i $TAPCHANGE $TAPCHANGEINTERVAL | grep "elapsedTime" >> op_log_$BLOCKSIZE
done



BLOCKSIZE=512
for i in "${DISPATCHSIZE[@]}"
do
        SPROFFILENAME="sprofv5_"$NOBLOCKS"_"$BLOCKSIZE"_"$i"_"$TAPCHANGE"_"$TAPCHANGEINTERVAL".csv"
        echo 'run '$SPROFFILENAME
        echo $SPROFFILENAME >> arg_list_$BLOCKSIZE
        $SPROFCOMMAND -o $SPROFFILENAME -w ./ ./bin/amd/fir_tap_change $NOBLOCKS $BLOCKSIZE $i $TAPCHANGE $TAPCHANGEINTERVAL | grep "elapsedTime" >> op_log_$BLOCKSIZE
done


