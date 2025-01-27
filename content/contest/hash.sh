# Hashea un archivo, ignorando todos los espacios en blanco y
# comentarios. Úsalo para verificar que el código fue escrito
# correctamente.
cpp -dD -P -fpreprocessed | tr -d '[:space:]'| md5sum | cut -c-6
