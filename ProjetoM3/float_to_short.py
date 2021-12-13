
def float_to_short(number_in_float:float)-> int:
    """
    Converts a float number to a C-language short
    """
    number_short = number_in_float*32768
    number_short = int(number_short)
    return number_short


def convert_coefs(coefs_float_filename: str)->None:
    """
    Accepts: txt filename without extention string
    Creates a new file with coefs converted to short
    """
    float_file = coefs_float_filename+".txt"
    new_file_name = coefs_float_filename+"_short.txt"
    data = []

    with open(float_file,'r') as f:
        d = f.readlines()
        for i in d:
            data.append(str(float_to_short(float(i))))
    with open(new_file_name,'w')as f:
        for new_value in data:
            f.write(new_value)
            f.write("\n")

convert_coefs("Coefs_PA_1k")