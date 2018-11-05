/*
* UTF-8 coding
*---------------------------------------------------------------------------------
* num		Byte 1		Byte 2		Byte 3		Byte 4		Byte 5		Byte 6
* 1			0xxxxxxx																
* 2			110xxxxx	10xxxxxx													
* 3			1110xxxx	10xxxxxx	10xxxxxx										
* 4			11110xxx	10xxxxxx	10xxxxxx	10xxxxxx							
* 5			111110xx	10xxxxxx	10xxxxxx	10xxxxxx	10xxxxxx				
* 6			1111110x	10xxxxxx	10xxxxxx	10xxxxxx	10xxxxxx	10xxxxxx
*---------------------------------------------------------------------------------
* change NOT UTF-8  char  to '?'
**/
int FilterUtf8String(uint8* str,long length)
{
    int i;
    int ret = 1; 
    for(i=0; i<length;)
    {
		if((str[i]) >= 0x80) // NOT ASCII
		{
			if((str[i] & 0xfe) == 0xfc)
            {
				// 6 bytes utf-8
				if((i+6) <= length)
				{
					if(((str[i+1] >> 6) != 0x02) || ((str[i+2] >> 6) != 0x02) || ((str[i+3] >> 6) != 0x02) ||
						((str[i+4] >> 6) != 0x02) || ((str[i+5] >> 6) != 0x02))
					{
						memset(&str[i],0x3F,6);
						ret = 0;
					}
					
					i=i+6;
				}
				else
				{
					int j = i;
					while(j < length)
					{
						str[j] = '?';
						j++;
						ret = 0;
					}
					
					i = length;
				}
				
				//str = str+i;
            }
			else if((str[i] & 0xfc) == 0xf8)
			{
				// 5 bytes utf-8
				if((i+5) <= length)
				{
					if(((str[i+1] >> 6) != 0x02) || ((str[i+2] >> 6) != 0x02) || ((str[i+3] >> 6) != 0x02) || ((str[i+4] >> 6) != 0x02))
					{
						memset(&str[i],0x3F,5);
						ret = 0;
					}
					
					i=i+5;
				}
				else
				{
					int j = i;
					while(j < length)
					{
						str[j] = '?';
						j++;
						ret = 0;
					}
					
					i = length;
				}
				
			}
			else if((str[i] & 0xf8) == 0xf0)
			{
				////4 bytes utf-8
				if((i+4) <= length)
				{
					if(((str[i+1] >> 6) != 0x02) || ((str[i+2] >> 6) != 0x02) || ((str[i+3] >> 6) != 0x02))
					{
						memset(&str[i],0x3F,4);
						ret = 0;
					}
					
					i=i+4;
				}
				else
				{
					int j = i;
					while(j < length)
					{
						str[j] = '?';
						j++;
						ret = 0;
					}
					
					i = length;
				}
				
			}
			else if((str[i] & 0xf0) == 0xe0)
			{
				////3 bytes utf-8
				if((i+3) <= length)
				{
					if(((str[i+1] >> 6) != 0x02) || ((str[i+2] >> 6) != 0x02))
					{
						memset(&str[i],0x3F,3);
						ret = 0;
						printf("not 3\n");
					}
					
					i=i+3;
				}
				else
				{
					int j = i;
					while(j < length)
					{
						str[j] = '?';
						j++;
						ret = 0;
					}
					i = length;
				}
			}
			else if((str[i] & 0xe0) == 0xc0)
			{
				////2 bytes utf-8
				if((i+2) <= length)
				{
					if(((str[i+1] >> 6) != 0x02))
					{
						memset(&str[i],0x3F,2);
						ret = 0;
					}
					
					i=i+2;
				}
				else
				{
					int j = i;
					while(j < length)
					{
						str[j] = '?';
						j++;
						ret = 0;
					}
					i = length;
				}
			}
			else
			{
				str[i] = '?';
				i=i+1;
				ret = 0;
			}
			
		}
		else
		{
			i=i+1;
		}
         
    
	}
	
	return ret;
}
