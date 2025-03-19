def split_input_file(input_filename):
    with open(input_filename, 'r', encoding='utf-8') as file:
        lines = file.readlines()
    
    file_count = 1
    current_lines = []
    output_filename = None
    output_section = False  # Flag para saber se já passou por uma linha "Output"
    
    for line in lines:
        if line.startswith("Input"):
            # Se já tivermos linhas acumuladas, escreve no arquivo atual
            if current_lines and output_filename:
                with open(output_filename, 'w', encoding='utf-8') as out_file:
                    out_file.writelines(current_lines)
            
                file_count += 1  # Aumenta o contador do arquivo
                current_lines = []  # Limpa as linhas acumuladas
            
            # Define o novo nome do arquivo de saída
            output_filename = f"teste{file_count}.txt"
            output_section = False  # Reinicia a flag para não ignorar linhas
        elif line.startswith("Output"):  # Quando encontra "Output", começa a ignorar as linhas
            output_section = True
        elif not output_section:  # Só adiciona as linhas antes de "Output"
            current_lines.append(line)
    
    # Escreve o último conjunto de linhas acumuladas, se existirem
    if current_lines and output_filename:
        with open(output_filename, 'w', encoding='utf-8') as out_file:
            out_file.writelines(current_lines)

# Chame a função passando o nome do arquivo de entrada
txt_filename = "entrada.txt"  # Altere para o nome correto do arquivo de entrada
split_input_file(txt_filename)
