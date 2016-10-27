#Map generator
1. Load the map image  
2. Go through each pixel  
  if pixel's colour is white then  
   * increase current territory ID by 1  
   * store territory's unique x,y coordinates  
   * recursively fill the white area  
  	 * if white, putpixel, do the same for pixels around - with unique colour calculated from ID (should use function for this one)    
3. Store the image for future reference ([territory picking](map_management.md#territory-picking-client))  

#Map drawing (client)  
1. Draw the map image  
2. Get server's info about occupied territories and countries  
3. Get IDs from server and corresponding information and do something like:  
  Territories[ID]->ownership->countries[x];  
  fillArea(Territory[ID]->getX(), Territory[ID]->getY());  

#Territory picking (client)
1. On mouseClick(x,y):  
2. Create a new matrix  
  Draw the unique-coloured map onto the matrix  
3. Get pixel from x,y  
4. Calculate ID from pixel colour  
5. Territories[ID]->whatever_you_need  
6. Get rid of the unique-coloured matrix and keep showing the user map  
