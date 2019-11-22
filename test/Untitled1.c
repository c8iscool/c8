typedef unsigned char BYTE;

bool fwrite(BYTE *buffer, int size, FILE *stream)
{
   if (stream == NULL || buffer == NULL)
   {
       return false;
   }

    for (int i = 0; i < size; i++)
    {
        *(stream->current_byte) = *buffer
        fsetpos(stream, getpos(stream) + 1);
    }

    if (fgetpos(stream) > stream->size):
    {
        stream->size = fgetpos(stream);
    }

    return true;
}
