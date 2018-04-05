
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>


void SHA256Hash(unsigned char digest[EVP_MAX_MD_SIZE], char *stringToHash);
void PrintSHA256Hash(unsigned char digest[EVP_MAX_MD_SIZE]);
    
int main(int argc, char **argv)
{
 unsigned char digest[EVP_MAX_MD_SIZE];

 if(argc != 2)
    {
    printf("Provide single argument to hash\n");
    exit(1);
    }
  
 SHA256Hash(digest, argv[1]);
 PrintSHA256Hash(digest);
 
 return 0;
}

void SHA256Hash(unsigned char digest[EVP_MAX_MD_SIZE], char *stringToHash)
{
 OpenSSL_add_all_digests();
 
 const EVP_MD *md = EVP_get_digestbyname("sha256");
 
 EVP_MD_CTX context;
 EVP_MD_CTX_init(&context);
 EVP_DigestInit_ex(&context, md, NULL); 
 EVP_DigestUpdate(&context, (unsigned char *)stringToHash, strlen(stringToHash));
 
 unsigned int digestSz;
 EVP_DigestFinal_ex(&context, digest, &digestSz);
 EVP_MD_CTX_cleanup(&context);
 
 EVP_cleanup();
}

void PrintSHA256Hash(unsigned char digest[EVP_MAX_MD_SIZE])
{
#define DIGEST_SIZE_BYTES (256 / 8)
#define DIGEST_SIZE_HEX (DIGEST_SIZE_BYTES * 2)

 char buf[DIGEST_SIZE_HEX + 1] = {0};

 int i;
 for(i = 0; i < DIGEST_SIZE_BYTES; i++)
    {
    snprintf(&(buf[2*i]), 3, "%02x", digest[i]);
    }


 MessageBox(NULL, buf, "Digest", MB_OK);
 
 //printf("Digest is: %s\n", buf);
}
