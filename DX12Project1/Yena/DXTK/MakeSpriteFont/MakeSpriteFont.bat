@echo off

REM ASCII 0 ~ 255 + Ư������'��' + Unicode �ѱ� �ϼ��� �� 11,440 ����
MakeSpriteFont "����" myfile.sfont /FontSize:9 /CharacterRegion:0x0-0xff /CharacterRegion:0x25a0 /CharacterRegion:0xAC00-0xD7AF  /DefaultCharacter:0x5f /FastPack


REM MakeSpriteFont "����" myfile.sfont /FontSize:10
REM MakeSpriteFont "���� ���" myfile.sfont /FontSize:10
REM MakeSpriteFont "Consolas" myfile.sfont /FontSize:10
