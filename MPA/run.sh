#
#Author: Andrew Snyder
#Created Date: July 17th, 2017
#
#

. $(dirname $0)/config.properties
. $HOME_FOLDER/db/cc.properties

#Turncating IC3 Database
#echo "Turncating Database"
#cat $HOME_FOLDER/db/ic3_truncate.sql | mysql -u$user -p$password cc


#Running IC3
#IC3=$HOME_FOLDER/ic3.sh
#find $HOME_FOLDER/Input/ -type f -name "*.apk"| while read APK_FILE;
#do
#	$IC3 $APK_FILE
#	RESULT=$?
#	if [ "$RESULT" -eq "0" ]; then
#		echo "Running IC3: Successful"
#	else
#		echo "Running IC3: Failed"
#	fi
#done

#Running parse program.
#cd $JITANA_IAC
#./launch --path $HOME_FOLDER/Input/
#cd $HOME_FOLDER
$HOME_FOLDER/Debug/MPA $JITANA_IAC/output $METHOD_GRAPH_PATH $user $password

