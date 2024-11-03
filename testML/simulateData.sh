nCores=6
teamPlate="teamplate.mac"
eventFin=670
nEvents=1000000
nLoops=500 # 5cores : 1output -> loop 200 -> 1000 output 
outputDir="./data"
mkdir -p "$outputDir"

iE=1001
for ((i=0; i < nLoops; i++))
do
  for ((core=1; core <= nCores; core++))
  do
    energy=$(($iE))
    macFile="simulation${energy}.mac"
    cp $teamPlate $macFile
    outputFile="output${energy}.root"

    echo "/gps/energy ${energy} keV" >> $macFile
    echo "/analysis/setFileName $outputFile" >> $macFile
    echo "/run/beamOn ${nEvents}" >> $macFile
    
    ./sim $macFile &
    ((iE++))
  done

  wait
  mv *root $outputDir
  rm simulation*.mac
done
