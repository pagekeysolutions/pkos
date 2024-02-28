AFTER entering VGA mode
-----
(gdb) p/x vga
$1 = {
  ac = {
    regPalettes = {0x20, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0x0, 0xe1, 0xc, 0x10, 0x0}, 
    regAttributeMode = 0x4, 
    regOverscanColor = 0x0, 
    regColorPlane = 0x0, 
    regHorizPixel = 0x0, 
    regPixelShift = 0x5
  }, 
  crtc = {
    regHorizTotal = 0x0, 
    regEndHorizDisplay = 0x0, 
    regStartHorizBlanking = 0x0, 
    regEndHorizBlanking = 0x0, 
    regStartHorizRetrace = 0xd6, 
    regEndHorizRetrace = 0xd, 
    regVertTotal = 0x10, 
    regOverflow = 0x0, 
    regPresetRowScan = 0x61, 
    regMaxScanLine = 0x0, 
    regCursorStart = 0x0, 
    regCursorEnd = 0x0, 
    regStartAddressHigh = 0x0, 
    regStartAddressLow = 0x0, 
    regCursorLocationHigh = 0x0, 
    regCursorLocationLow = 0x4d, 
    regVertRetraceStart = 0x7, 
    regVertRetraceEnd = 0x10, 
    regVertDisplayEnd = 0x0, 
    regOffset = 0x1c, 
    regUnderlineLocation = 0x60, 
    regStartVertBlanking = 0x10, 
    regEndVertBlanking = 0x0, 
    regModeControl = 0xf8, 
    regLineCompare = 0xf}, 
  ext = {
    regMisc = 0x10, 
    regFeature = 0x0, 
    regInputStatus0 = 0x4f, 
    regInputStatus1 = 0x32
  }, 
  gc = {
    regSetReset = 0x10, 
    regEnableSetReset = 0x0, 
    regColorCompare = 0x3, 
    regDataRotate = 0x0, 
    regReadMap = 0x0, 
    regGraphicsMode = 0x0, 
    regMisc = 0x3c, 
    regColorDontCare = 0x60, 
    regBitMask = 0x10
  }, 
  seq = {
    regReset = 0x0, 
    regClocking = 0xf2, 
    regMapMask = 0x9, 
    regCharMapSelect = 0x10, 
    regSeqMemoryMode = 0x0
  }
}
