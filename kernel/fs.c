#include "fs.h" 

uint16_t fat[NUM_CLUSTERS];
struct superblock_t superblock;

struct dir_entry_t directory[MAX_FILES];



int fs_init(void)
{
	superblock.magic = SIMPLEFAT_MAGIC;
	superblock.cluster_size = CLUSTER_SIZE;
	superblock.total_clusters = TOTAL_CLUSTERS;
	superblock.total_blocks = TOTAL_BLOCKS; //WARN: Potentially this value is wrong

	for(uint32_t i = 0; i < NUM_CLUSTERS; i++) {
		fat[i] = FAT_FREE;
	}

	for(uint32_t i = 0; i < MAX_FILES; i++) {
		directory[i].first_cluster = 0x0000;
		directory[i].name[0] = '\0';
		directory[i].size = 0;
	}

	return 0;
}

int cluster_alloc(void)
{
	for(uint32_t i = 0; i < NUM_CLUSTERS; i++)
	{
		if(!fat[i])
			return i;
	}

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

