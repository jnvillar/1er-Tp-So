if [ $# -eq 0 ]; then
    echo -e "\nUso: \n\n\t ./run.sh [argumentos_para_el_simusched]\n\n"
    exit 1
fi

echo -e '\0033\0143' && make clean && make && ./simusched $@ | python graphsched.py >> imagen.png