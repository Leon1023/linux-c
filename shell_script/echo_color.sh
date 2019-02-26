#!/data/data/com.termux/files/usr/bin/bash

#方法一：
    if [ $1 = "green" ]; then
        echo -e "\033[32;40m$2\033[0m"
    elif [ $1 = "red" ]; then
        echo -e "\033[31;40m$2\033[0m"
    else
        echo "Usage: echo_color red/green string"
    fi

#方法二：
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

