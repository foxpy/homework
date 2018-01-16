import subprocess
from mtranslate import translate

process = subprocess.Popen("python -c \"import this\"",
        stdout = subprocess.PIPE, shell = True)
(output, err) = process.communicate()
p_status = process.wait()

print(translate(output, "ru", "en"))

