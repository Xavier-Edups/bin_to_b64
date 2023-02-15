#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>

int _encode_64_triplet(char *triplet, int32_t triplet_size, char *encoded_triplet);

// void _encode_64_triplet_c(char *triplet, int32_t triplet_size, char *encoded_triplet)
// {
//   char *base_64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
//   uint32_t triplet_value = (triplet[0] << 16) | (triplet[1] << 8) | triplet[2];
//   encoded_triplet[0] = base_64_table[(triplet_value >> 18) & 0x3F];
//   encoded_triplet[1] = base_64_table[(triplet_value >> 12) & 0x3F];
//   encoded_triplet[2] = base_64_table[(triplet_value >> 6) & 0x3F];
//   encoded_triplet[3] = base_64_table[triplet_value & 0x3F];
//   if (triplet_size < 3)
//     encoded_triplet[3] = '=';
//   if (triplet_size < 2)
//     encoded_triplet[2] = '=';
// }

char *get_filename(int argc, char **argv)
{
  if (argc != 2)
  {
    printf("Invalid number of arguments.\nUsage: bin_to_b64 <file>\n");
    exit(1);
  }
  return argv[1];
}

char *readFile(const char *filename, size_t *size)
{
  FILE *fp = fopen(filename, "rb");
  if (!fp)
  {
    perror("readFile error\n");
    exit(1);
  }
  fseek(fp, 0, SEEK_END);
  size_t len = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  char *data = malloc(len);
  fread(data, 1, len, fp);
  fclose(fp);
  *size = len;
  return data;
}

char *encode_64_string(const char *data, size_t size, size_t *encoded_size)
{
  *encoded_size = ((size + 2) / 3) * 4;
  char *encoded = (char *)malloc(*encoded_size);
  printf("encoded_size: %ld\n", *encoded_size);
  for (size_t i = 0, j = 0; i < size; i += 3, j += 4)
  {
    char triplet[3];
    char encoded_triplet[4];
    triplet[0] = data[i];
    triplet[1] = i + 1 < size ? data[i + 1] : 0;
    triplet[2] = i + 2 < size ? data[i + 2] : 0;
    int32_t triplet_size = i + 2 < size ? 3 : i + 1 < size ? 2
                                                           : 1;
    int returned = _encode_64_triplet(triplet, triplet_size, encoded_triplet);
    printf("encoded_triplet[0] = 0x%x\n", encoded_triplet[0]);
    // _encode_64_triplet(triplet, triplet_size, encoded_triplet);
    // encoded[j] = encoded_triplet[0];
    // encoded[j + 1] = encoded_triplet[1];
    // encoded[j + 2] = encoded_triplet[2];
    // encoded[j + 3] = encoded_triplet[3];
  }
  return encoded;
}

int main(int argc, char **argv)
{
  char *filename = get_filename(argc, argv);
  size_t size;
  char *data = readFile(filename, &size);
  for (int i = 0; i < size; i++)
    printf("%d\n", data[i]);
  size_t encoded_size;
  char *encoded = encode_64_string(data, size, &encoded_size);
  for (size_t i = 0; i < encoded_size; i++)
  {
    printf("%c\n", encoded[i]);
  }
  free(data);
  free(encoded);
}