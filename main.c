/** REQUIRIMENTS
 * 10 imagenes en grises y 10 en color
 * - sumar 1 imagen de color con una en grises preseleccionada y guardar el resultado
 * - Producto cartesiano de las 10 imagenes grises
 * - Producto cartesiano de las 20 imagenes (color y grises)
 * - restar a 1 imagen de color una imagen gris
 * 
 * Nota: Producto Cartesiano es 1px * toda la otra imagen, es decir 128px*128px=16384px 
 */
#include "imageoperator.h"
#include "cronometer.h"
#include <stdio.h>
#define VALIDSIZE 128 //Constante para definir el tamaño de la imagen
#define UNION2FUNS(X, Y) { X; Y; }

void getImageWValidation(Image *img); //Firma de la funcion "getImageWValidation"

int main()
{
    Image img1, img2, imgSepia, imgGrey; //declaracion de variables tipo image
    Image *arrImgColor = malloc(sizeof(Image) * 10), //declaracion de arreglo dinamico para imagen de color
          *arrImgGrey = malloc(sizeof(Image) * 10), //declaracion de arreglo dinamico para imagen en blanco y negro
          *arrImgPlus = malloc(sizeof(Image) * 10), //declaracion de arreglo dinamico para resultado de la suma de imagenes
          *arrImgMinus = malloc(sizeof(Image) * 10), //declaracion de arreglo dinamico para resultado de resta de imagenes
          *arrImgCartesian = malloc(sizeof(Image) * 20), //declaracion de arreglo dinamico para el producto cartesiano de imagenes grises
          *arrImgCartesianColor = malloc(sizeof(Image) * 10); //declaracion de arreglo dinamico para el producto cartesiano de imagenes de color y grises

    getImageWValidation(&img1); //validar imagen
    //getImageWValidation(img2);

    // Operates images
//    image2Grey(&img1, &imgGrey);

    CRONO_THIS(UNION2FUNS(image2Grey(&img1, &imgGrey), imageSave(&imgGrey)));
    /*imageSave(&imgGrey) guarda las imagenes resultantes
    image2Grey(&img1, &imgGrey) transforma una imagen a blanco y negro
    UNION2FUNS(image2Grey(&img1, &imgGrey), imageSave(&imgGrey)) ejecuta 2 sentencias
    CRONO_THIS(UNION2FUNS(image2Grey(&img1, &imgGrey), imageSave(&imgGrey))) cronometra lo que tarda en ejecutarse una declaracion
    */

    imageFree(&img1); //libera la memoria de img1
    imageFree(&imgGrey); //libera la memoria de imgGrey

    char command[300] = ".\\";
    strcat(command, imgGrey.name);
    system(command);
}

void getImageWValidation(Image *img) //Funcion para validar los formatos de la imagen
{
    while (1) // Validación completa para entrada de imagen
    {
        char path[260]; //arreglo de caracteres para la ruta de la imagen

        printf("ruta de imagen: "); //impresion de texto "ruta de imagen"
        scanf("%s", path); //lectura de la ruta de la imagen

        if (strlen(path) == 0) //validación de que se ingresa ruta
            printf("ERROR: Ingresa una ruta \n"); //impresion de texto para que el usuario sepa que no esta ingresando una ruta
        else if (strchr(path, '.') == NULL)//validación de que tiene la extencion la ruta
            printf("Incluye la externsion \n");//impresión de texto para indicarle al usuario que incluya la ruta
        else if (strstr(path, ".jpg") == NULL && strstr(path, ".png") == NULL && strstr(path, ".gif") == NULL && strstr(path, ".bmp") == NULL) //validacion de los formatos a utilizar para las imagenes
            printf("Externsion no valida. Solo jpg, png, gif, bmp \n"); //impresion de texto para indicar si el tipo de dato no es compatible
        else if (!imageLoad(img, path)) //validacion de que la imagen existe
            printf("el archivo \"%s\" no existe \n", path); //impresion de texto para indicarle al usuario que la imagen no existe
        else if (img->width != VALIDSIZE || img->height != VALIDSIZE)//validacion del tamaño de la imagen
            printf("el archivo \"%s\" debe medir %dpx x %dpx \n", path, VALIDSIZE, VALIDSIZE);// impresion de texto para indicarle al usuario el tamaño de la imagen
        else break; //se rompe el ciclo
    }
}
