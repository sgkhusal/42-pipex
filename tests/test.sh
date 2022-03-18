# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sguilher <sguilher@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/16 22:02:02 by sguilher          #+#    #+#              #
#    Updated: 2022/03/16 22:02:04 by sguilher         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

#cd ..
#make

# error messages 
echho 123 # command not found

# arquivo de entrada não existe
< infile ls -l | wc -l > outfile # errno 2, não roda o primeiro comando, mas roda o segundo
grep
grep p
< error.txt > outfile #(arquivo de input existe, cria o arquivo de saída)
< infile catzzz | wc -w > outfile #não roda o primeiro comando (dá erro), mas roda o segundo
< infile catzzz | bonjour | wc -l > outfile #não roda o primeiro e o segundo comando (dá erro), mas roda o segundo