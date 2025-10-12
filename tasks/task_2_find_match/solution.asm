immediate + 63;
cp_from_reg0 + 1;
immediate + 1;
cp_from_reg0 + 2;

label g_less;

add;

label g_greater;

cp_from_reg3 + 1;
cp_from_reg3 + 6;
cp_from_input + 3;

g_less;
jz;
sub;
g_greater;
jump;

