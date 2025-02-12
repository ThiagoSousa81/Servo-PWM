# Servo e PWM

### Controle de um servomotor usando a interface PWM do RP2040

É assim que é definida a frequência do PWM:

<h3 align=center> 

$f_{PWM}\ =\ \frac{f_{clock}}{\left(divisor\ inteiro+\frac{divisor\ fracionario}{16}\right)\cdot wrap}$ 

</h3>

$f_{PWM}$: Frequência do PWM<br>
$f_{clock}$: Frequência do sinal de Clock<br>
$divisor\ inteiro$: Parte inteira do divisor de clock (8 bits)<br>
$divisor\ fracionario$: Parte fracionária do divisor de clock (4 bits)<br>
$wrap$: Valor máximo de contagem. Possui 16 bits