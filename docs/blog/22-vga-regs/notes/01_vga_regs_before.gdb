BEFORE entering VGA mode
------
(gdb) p/x vga
$1 = {
  ac = {
    regPalettes = {0x0, 0x61, 0x0, 0x0, 0x0, 0x4, 0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0x0, 0xd6, 0xd, 0x10}, 
    regAttributeMode = 0x0, 
    regOverscanColor = 0x4, 
    regColorPlane = 0x0, 
    regHorizPixel = 0x0, 
    regPixelShift = 0x0
  }, 
  crtc = {
    regHorizTotal = 0x5, 
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
    regCursorLocationLow = 0x0, 
    regVertRetraceStart = 0x4d, 
    regVertRetraceEnd = 0x7, 
    regVertDisplayEnd = 0x10, 
    regOffset = 0x0, 
    regUnderlineLocation = 0x20, 
    regStartVertBlanking = 0x0, 
    regEndVertBlanking = 0x0, 
    regModeControl = 0x0, 
    regLineCompare = 0x0
  }, 
  ext = {
    regMisc = 0x0, 
    regFeature = 0x0, 
    regInputStatus0 = 0x0, 
    regInputStatus1 = 0x20
  }, gc = {
    regSetReset = 0x40, 
    regEnableSetReset = 0x10, 
    regColorCompare = 0x0, 
    regDataRotate = 0x3, 
    regReadMap = 0x0, 
    regGraphicsMode = 0x0, 
    regMisc = 0x0, 
    regColorDontCare = 0xfc, 
    regBitMask = 0x5f
  }, 
  seq = {
    regReset = 0x10, 
    regClocking = 0x0, 
    regMapMask = 0x90, 
    regCharMapSelect = 0xa, 
    regSeqMemoryMode = 0x10
  }
}