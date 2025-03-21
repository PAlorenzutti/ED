def split_input_file(input_filename):
    with open(input_filename, 'r', encoding='utf-8') as file:
        lines = file.readlines()
    
    file_count = 0
    current_lines = []
    output_filename = None
    in_output = False  # Flag para controlar se estamos em uma seção de Output
    
    for line in lines:
        if line.startswith("Input"):
            if in_output:
                # Se encontrar Input e estiver em Output, finaliza o arquivo atual
                if current_lines and output_filename:
                    with open(output_filename, 'w', encoding='utf-8') as out_file:
                        out_file.writelines(current_lines)
                    current_lines = []
                    in_output = False
        elif line.startswith("Output"):
            # Se encontrar novo Output, finaliza o arquivo anterior (se houver) e inicia novo
            if in_output:
                if current_lines and output_filename:
                    with open(output_filename, 'w', encoding='utf-8') as out_file:
                        out_file.writelines(current_lines)
                    current_lines = []
                    file_count += 1
            else:
                file_count += 1
            output_filename = f"diff{file_count}.txt"
            in_output = True
        elif in_output:
            current_lines.append(line)
    
    # Escreve qualquer conteúdo restante após o loop
    if in_output and current_lines and output_filename:
        with open(output_filename, 'w', encoding='utf-8') as out_file:
            out_file.writelines(current_lines)

# Chamada da função
txt_filename = "entrada.txt"
split_input_file(txt_filename)