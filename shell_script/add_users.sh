#!/data/data/com.termux/files/usr/bin/bash
#Creat 10 users at onece
DATE=$(date +%F_%T)
USER_FILE=user.txt
echo_color(){
    case $1 in
        green)
            echo -e "\033[32;40m$2\033[0m"
            ;;
        red)
            echo -e "\033[31;40m$2\033[0m"
            ;;
        *)
            echo "Usage: echo_color red/green string"
    esac
}

#if there is a user.txt ,and backup
if [ -s $USER_FILE ]; then
    mv $USER_FILE ${USER_FILE}-${DATE}.bak
    echo_color green "$FILE_USER exist,rename it to ${USER_FILE}-${DATE}"
fi
echo -e "User\tPassword" >> $USER_FILE
echo -e "--------------" >> $USER_FILE
for USER in user{1..10}; do
    if ! id $USER &> /dev/null; then
        PASS=$(echo $RANDOM | md5sum | cut -c 1-8 )
        useradd $USER &>/dev/null
        echo $PASS | passwd --stdin $USER &>/dev/null
        echo -e "$USER\t$PASS" >> $USER_FILE
        echo -e "$USER user creat success!"
    else
        echo_color red -e "$USER user already exist!"
    fi
done


