### Шифр Вернама

#### [Условие задачи](https://sites.google.com/site/pathofdeveloper/zadaci-vtorogo-semestra/sifr-vernama) | [Тестер](https://sites.google.com/site/pathofdeveloper/zadaci-vtorogo-semestra/sifr-vernama/freqs.zip?attredirects=0&d=1)

Обязательное требование: нужно уметь шифровать не только текстовые, но и бинарные файлы, например сам шифровальщик. После шифрования-дешифрования должен получится файл, идентичный оригинальному:
	vernam.exe "some semi-secret key" < vernam.exe > encrypted_vernam.exe
	vernam.exe "some semi-secret key" < encrypted_vernam.exe > new_vernam.exe