#include "fs.h" 

int fs_init(void)
{
	/*
	* TODO:
	* Inicializar superbloco.
	*/
	/*
	* TODO:
	* Inicializar FAT.
	*/
	/*
	* TODO:
	* Inicializar diretrio.
	*/
	return 0;
}

int cluster_alloc(void)
{
	/*
	* TODO:
	* Procurar FAT_FREE.
	*/
	return -1;
}

int fs_create(const char *name)
{
	/*
	 * TODO:
	 * Procurar entrada livre.
	 */
	/*
	 * TODO:
	 * Alocar cluster inicial.
	 */
	/*
	 * TODO:
	 * Atualiza Diretório
	 */

	return 0;
}

int fs_open(const char *name)
{
	/*
	 * TODO:
	 * Localizar entrada.
	 */

	return 0;
}

int fs_write(int fd, const void *buffer, uint32_t size)
{
	/*
	 * TODO:
	 * Alocar clusters.
	 */

	/*
	 * TODO:
	 * Atualizar FAT.
	 */
	/*
	 * TODO:
	 * Copiar dados.
	 */
	return size;
}

int fs_read(int fd, void *buffer, uint32_t size)
{
	/*
	 * TODO:
	 * Percorrer FAT.
	 */

	/*
	 * TODO:
	 * Copiar dados.
	 */

	return size;
}

int fs_close(int fd)
{
	/*
	 * TODO:
	 * Liberar descritor de arquivos
	 */

	return 0;
}

int fs_delete(const char *name)
{
	/*
	* TODO:
	* Localizar arquivo.
	*/
	/*
	* TODO:
	* Liberar clusters.
	*/
	/*
	* TODO:
	* Remover entrada.
	*/
	return 0;
}

