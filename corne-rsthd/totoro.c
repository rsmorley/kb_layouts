
// 'totoro0', 32x32px
const char epd_bitmap_totoro0 [] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 
	0x01, 0xf3, 0xc1, 0x13, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xdf, 0xff, 0xef, 0xef, 0xef, 0xef, 0xe7, 0xe1, 0xe0, 
	0xc0, 0xdf, 0xbf, 0x3e, 0x44, 0xd1, 0xc3, 0x77, 0x8f, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x3f, 0x3f, 0x3f, 0x00, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0xdf, 0xcf, 0xef, 0xf7, 
	0xf3, 0xfb, 0xfb, 0xbd, 0x00, 0xe0, 0xdc, 0xdf, 0xdd, 0xfd, 0xfd, 0x07, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0xfc, 0xf8, 0xc0, 0x80, 0x00, 0x03, 0x0f, 0x0f, 0x1f, 
	0x9f, 0x9f, 0x87, 0x99, 0xbc, 0x9f, 0x9f, 0x8f, 0x8f, 0x8f, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff
};
// 'totoro1', 32x32px
const char epd_bitmap_totoro1 [] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 
	0x01, 0xf1, 0xc1, 0x03, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x9f, 0xef, 0xf7, 0xf7, 0xf7, 0xf7, 0xf7, 0xf1, 0xe0, 
	0xe0, 0xcf, 0xdf, 0xbf, 0x66, 0xc9, 0x41, 0x33, 0xa7, 0x8f, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x9f, 0x1f, 0x1f, 0x10, 0x1f, 0x1f, 0x1f, 0x1f, 0x0f, 0xcf, 0xef, 0xf7, 0xf3, 
	0xfb, 0xfd, 0xbd, 0x9d, 0x01, 0xe0, 0xdc, 0xdd, 0xe8, 0xf5, 0xfc, 0x83, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0xfc, 0xf0, 0xe0, 0xe0, 0xc3, 0x87, 0x8f, 0x8f, 
	0x8f, 0x8f, 0x1f, 0x01, 0x9c, 0x9f, 0xef, 0xef, 0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff
};
// 'totoro2', 32x32px
const char epd_bitmap_totoro2 [] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 
	0x01, 0xf3, 0xc1, 0x07, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xef, 0xff, 0xf7, 0xf7, 0xf7, 0xf7, 0xf1, 0xf0, 
	0xe0, 0xef, 0xdf, 0xbe, 0x44, 0xd1, 0xc3, 0x77, 0x8f, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xbf, 0x3f, 0x3f, 0x3f, 0x38, 0x3f, 0x1f, 0x1f, 0x1f, 0x1f, 0xdf, 0xcf, 0xef, 0xe7, 
	0xf3, 0xfb, 0xfb, 0xbd, 0x81, 0x80, 0x1c, 0xdd, 0xd9, 0xf5, 0xfd, 0x07, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xfc, 0xc0, 0x80, 0x80, 0x80, 0x80, 0x83, 0x87, 0x8f, 0x8f, 
	0x9f, 0x9f, 0x1f, 0x1f, 0x3f, 0x7f, 0x7c, 0x71, 0x87, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 400)
const int epd_bitmap_allArray_LEN = 3;
const char* epd_bitmap_allArray[3] = {
	epd_bitmap_totoro0,
	epd_bitmap_totoro1,
	epd_bitmap_totoro2
};
