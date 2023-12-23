; Programmbereich:

anf:  MOV EDX,400000H
      MOV [verzoe],EDX
m1: MOV EDI,10
 MOV ESI,OFFSET ziff ;Adresse von ziff ins Register bringen
 ;(siehe Erlaeuterung)
 m2: MOV AL,[ESI+EDI-1]
 OUT 0B0H,AL
 CALL zeit
 DEC EDI
 JNZ m2
 MOV AL,0FFH
 m3: OUT 5CH,AL
     NOT AL
     OUT 5DH,AL
     CALL zeit
     
     MOV BL,AL ; Inhalt von AL wird noch gebraucht
     IN AL,59H
     BT EAX,7
     MOV AL,BL ;AL bekommt alten Wert zurueck (CF bleibt)
     JC m1
     JMP m3

;zeit ist ein Unterprogramm, welches nur Zeit verbrauchen soll:
zeit: MOV ECX,[verzoe]
z1: DEC ECX
    JNZ z1
    RET
 ; Datenbereich:
 verzoe DD ? ;Eine Speicherzelle (Doppelwort).
 ;Anfangsbelegung ist undefiniert.
 ziff DB 3FH,03H,6DH,67H,53H,76H,7EH,23H,7FH,77H
 ;Zehn Speicherzellen (Bytes).
 ;Anfangsbelegung sind die Sieben-Segment-
 ;Kodierungen der Ziffern Null bis Neun. 