
use uo;

include ":gumps:gumps";
include ":gumps:gumps_ex";

function AutoCheckBox(mobile, prompt, options, returnKeys := 0)

	var sizex;
	var sizey;

	var columns := options.size()/20;
	if ( columns <= 1 )
		sizey := 40 + options.size()*20;
		if (sizey > 540)
			sizey := 540;
		endif
		if (sizey < 160)
			sizey := 160;
		endif
		sizex := 200;
		if ( (options.size() % 20) > 0)
			sizex := sizex + 150;
		endif
	else
		sizey := 540;
		sizex := 40 + cint(columns) * 150;
		if ( (options.size() % 20) > 0)
			sizex := sizex + 150;
		endif
		if (sizex > 800)
			sizex := 800;
		endif
		
	endif

	var gump := GFCreateGump(40, 40);
	GFClosable(gump, 0);
	GFResizePic(gump, 0, 0, 3600, sizex, sizey);
	GFResizePic(gump, 15, 15, 0x13BE, sizex-30, sizey-30);

	var y_pos := 20;
	foreach line in (GFWordWrap(prompt, 360))
		GFTextLine(gump, 20, y_pos, 1153, line);
		y_pos := y_pos+20;
		SleepMS(2);
	endforeach

	GFSetRadioGroup(gump, 1);
	var indice := 1;
	y_pos := 70;
	var first := 1;
	
	var y := 0;
	var x := 0;
	while(y <= columns)
		var maxx := 20;
		if (y == columns)
			maxx := options.size() % 20;
		endif
		while (x < maxx)
			GFTextLine(gump, 60 + y*150, y_pos + x*20, 1153, options[indice]);
			GFCheckBox(gump, 30 + y*150, y_pos + x*20, 210, 211, first, indice);
			first := 0;
			indice := indice+1;
			x := x + 1;
		endwhile
		x := 0;
		y := y + 1;
		indice := indice + 1;
	endwhile

	//foreach text in options
	//	GFTextLine(gump, 60, y_pos + indice*20, 1153, options[indice]);
	//	GFCheckBox(gump, 30, y_pos + indice*20, 210, 211, first, indice);
	//	first := 0;
	//	indice := indice+1;
	//endforeach
	
	GFAddButton(gump, sizex-70, sizey-60, 4502, 4502, 1, 999 );
	GFTextLine(gump, sizex-110, sizey-50, 1153, "Proximo");
  
	var ret := array;
  
	var input := GFSendGump(mobile, gump);
	if ( input[0] == 999 )
		 foreach key in (input.keys)
        		if (options[key]  )
				if (returnKeys)
					ret.append(key);
				else
          				ret.append(options[key]);
				endif
        		endif
     		endforeach
     		return ret;
  	else
      		return 0;
	endif	

endfunction

/* CheckBoxGump cria um gump com varias checkbox onde pode retornar varios valores clicados
   RadioGump cria um gump com varias radiosbuttons, mas apenas um botao pode ser retornado */

function CheckBoxGump(mobile, sizex, sizey, prompt:="", options, opts := 0)

	var gump := GFCreateGump(140, 100);
	GFClosable(gump, 0);
	GFResizePic(gump, 0, 0, 3600, sizex, sizey);
	GFResizePic(gump, 15, 15, 0x13BE, sizex-30, sizey-30);
	
	var y_pos := 20;
	foreach line in (GFWordWrap(prompt, 360))
		GFTextLine(gump, 20, y_pos, 1153, line);
		y_pos := y_pos+20;
		SleepMS(2);
	endforeach
	
  GFSetRadioGroup(gump, 1);
  var indice := 1;
  y_pos := 30;
  var first := 1;
  foreach text in options
    GFTextLine(gump, 60, y_pos + indice*20, 1153, text);
    if (opts)
      first := opts[indice];
    endif
    GFCheckBox(gump, 30, y_pos + indice*20, 210, 211, first, indice);
    first := 0;
    indice := indice+1;
  endforeach
	
  GFAddButton(gump, sizex-70, sizey-60, 4502, 4502, 1, 999 );
	GFTextLine(gump, sizex-110, sizey-50, 1153, "Proximo");
  
  var ret := array;
  
	var input := GFSendGump(mobile, gump);
	if ( input[0] == 999 )
		 foreach key in (input.keys)
        if (options[key]  )
          ret.append(options[key]);
        endif
     endforeach
     return ret;
  else
      return 0;
	endif	

endfunction

function RadioGump(mobile, sizex, sizey, prompt:="", options)

	var gump := GFCreateGump(140, 100);
	GFClosable(gump, 0);
	GFResizePic(gump, 0, 0, 3600, sizex, sizey);
	GFResizePic(gump, 15, 15, 0x13BE, sizex-30, sizey-30);
	
	var y_pos := 20;
	foreach line in (GFWordWrap(prompt, 360))
		GFTextLine(gump, 20, y_pos, 1153, line);
		y_pos := y_pos+20;
		SleepMS(2);
	endforeach
	
  GFSetRadioGroup(gump, 1);
  var indice := 1;
  y_pos := 30;
  var first := 1;
  foreach text in options
    GFTextLine(gump, 60, y_pos + indice*20, 1153, text);
    GFRadioButton(gump, 30, y_pos + indice*20, 210, 211, first, indice);
    first := 0;
    indice := indice+1;
  endforeach
	
  GFAddButton(gump, sizex-70, sizey-60, 4502, 4502, 1, 999 );
	GFTextLine(gump, sizex-110, sizey-50, 1153, "Proximo");
  
	var input := GFSendGump(mobile, gump);
	if ( input[0] == 999 )
		 foreach key in (input.keys)
        if (options[key]  )
          return options[key];
        endif
     endforeach
  else
      return 0;
	endif	
  
endfunction

  
function BigRequestGump(who, question := "")

	var gump := GFCreateGump();
	GFDisposable(gump, 0);
	GFResizePic(gump, 15, 50, 2620, 310, 380);
	
	var num_lines := 19;
	var msg_array := array;
	var y_pos := 55;
	var i;
	for ( i:=1; i<=num_lines; i:=i+1 )
		msg_array.Append(GFTextEntry(gump, 20, y_pos, 595, 20, 2100, ""));
		y_pos := y_pos+19;
	endfor

	GFResizePic(gump, 15, 20, GFCfgConst("Defaults", "ForeGround"), 310, 30);
	GFResizePic(gump, 15, 431, GFCfgConst("Defaults", "ForeGround"), 310, 30);

	GFAddButton(gump, 285, 441, 4011, 4030, GF_CLOSE_BTN, 20);
	GFTextLine(gump, 225, 441, 2100, "Terminar");
	GFTextLine(gump, 34, 23, 2100, question);

	var input := GFSendGump(who, gump);

	if (input[0] == 20)
		var i;
		for ( i:=1; i<=msg_array.Size(); i:=i+1 )
			var line := GFExtractData(input, msg_array[i]);
      //sendsysmessage(who, "extraindo linha " + line);
			if ( line )
				line := line + " ";
				msg_array[i] := line;
			else
				msg_array[i] := "";
			endif
      //sendsysmessage(who, "linha final " + line);
		endfor
	
		//Clear off empty lines.
		for ( i := msg_array.Size(); i>=1; i:=i-1 )
			if ( Len(msg_array[i]) <= 0 )
				msg_array.Erase(i);
			endif
			SleepMS(2);
		endfor
		
		var text := "";
		for ( i:=1; i<=msg_array.Size(); i:=i+1 )
			text := text + msg_array[i];
			SleepMS(2);
		endfor
		
		return text;
	endif
endfunction


function SmallRequestGump(who, question := "", addBR := 0)

	var gump := GFCreateGump();
	GFResizePic(gump, 15, 50, 2620, 150, 100);
	
	var num_lines := 5;
	var msg_array := array;
	var y_pos := 55;
	var i;
	for ( i:=1; i<=num_lines; i:=i+1 )
		msg_array.Append(GFTextEntryLimited(gump, 20, y_pos, 595, 20, 2100, "", 0, 22));
		y_pos := y_pos+19;
	endfor

	GFResizePic(gump, 15, 20, GFCfgConst("Defaults", "ForeGround"), 150, 30);
	GFResizePic(gump, 15, 150, GFCfgConst("Defaults", "ForeGround"), 150, 30);

	GFAddButton(gump, 130, 150, 4011, 4030, GF_CLOSE_BTN, 20);
	GFTextLine(gump, 75, 150, 2100, "Termina");
	GFTextLine(gump, 35, 20, 2100, question);

	var input := GFSendGump(who, gump);

	if (input[0] == 20)
		var i;
		for ( i:=1; i<=msg_array.Size(); i:=i+1 )
			var line := GFExtractData(input, msg_array[i]);
			if ( line )
				line := line + " ";
				if (addBR)
					msg_array[i] := line + "<br> ";
				else
					msg_array[i] := line;
				endif
			else
				msg_array[i] := "";
			endif
		endfor
	
		//Clear off empty lines.
		for ( i:=msg_array.Size(); i>=1; i:=i-1 )
			if ( Len(msg_array[i]) <= 0 )
				msg_array.Erase(i);
			endif
			SleepMS(2);
		endfor
		
		var text := "";
		for ( i:=1; i<=msg_array.Size(); i:=i+1 )
			text := text + msg_array[i];
			//sendsysmessage(who, " " + text);
			SleepMS(2);
		endfor
		
		return text;
	endif
endfunction
