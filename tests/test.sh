# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/16 22:02:02 by sguilher          #+#    #+#              #
#    Updated: 2022/03/25 21:01:24 by sguilher         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

#cd ..
#make

# error messages 
echho 123 # command not found

## ------------------ arquivo de entrada não existe ------------------------##
< infile ls -l | wc -l > outfile # errno 2, não roda o primeiro comando, mas roda o segundo
grep
grep p

< error.txt > outfile
#(arquivo de input existe, cria o arquivo de saída)

< infile catzzz | wc -w > outfile
#não roda o primeiro comando (dá erro), mas roda o segundo

< infile catzzz | bonjour | wc -l > outfile
#não roda o primeiro e o segundo comando (dá erro), mas roda o segundo

< infile lss | wcc -l > outfile
## ambos comandos não existem e arquivo de entrada não existe:
# msg de erro "bash: infile: No such file or directory"
# msg de erro "bash: wcc: command not found" apenas para o último comando
# cria o arquivo de outfile ou deixa ele vazio se ele existe

## ------------------ arquivo de entrada existe ------------------------##
## ambos comandos não existem
< infile lss | wcc -l > outfile
# cria o arquivo de outfile ou deixa ele vazio se ele existe
# msg de erro "bash: lss: command not found"
# msg de erro "bash: wcc: command not found"


# < swim_good "" | tr 'o' '0' > outfile
# bash: : command not found
# cria o outfile

#< swim_good "" | "" > outfile
#bash: : command not found
#bash: : command not found

#< swim_good grep swim |  > outfile ou
#< swim_good grep swim | > outfile
#não joga nada no terminal