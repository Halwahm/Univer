   M S B A M L   `   `   `  ����A  =lab4-5, Version=1.0.0.0, Culture=neutral, PublicKeyToken=nullclr-namespace:lab4_5lab4_5  5   	       lab4_5.AddAndChangeWindow   5   	   W SPresentationCore, Version=6.0.2.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=6.0.2.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35e aSystem.Windows.Controls.Ribbon, Version=6.0.2.0, Culture=neutral, PublicKeyToken=b77a5c561934e089R NWindowsBase, Version=6.0.2.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35F 9http://schemas.microsoft.com/winfx/2006/xaml/presentation     5   	   R NSystem.Xaml, Version=6.0.2.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   &localclr-namespace:lab4_5     5   	   _ [MaterialDesignThemes.Wpf, Version=4.7.1.0, Culture=neutral, PublicKeyToken=df2a72020bd7962aFmaterialDesign1http://materialdesigninxaml.net/winfx/xaml/themes  5   	      dic_Add  � Title#  �   5	   	   $	��500��6+   $	��240��68    � 
ResizeMode$ NoResize=�6D   .��5
      �   DefaultGrid#���  6    � ColumnDefinitions 5   
   �� 5      $	��41* �6   �� 5      $
��199* �6   .+�5   
   ��   dic_ProductsName#���  6   $
��Left=�6=   $��	10,10,0,0q�6X   $	��Top=�6k   $��2��6�   �� 5   
     dic_ProductsPrice#���  6   $
��Left=�6>   $��	10,39,0,0q�6Y   $	��Top=�6l   $��2��6�   �� 5   
     dic_ProductsRating#���  6   $
��Left=�6?   $��	10,68,0,0q�6Z   $	��Top=�6m   $��2��6�   �� 5   
     	dic_Photo#���  6   $
��Left=�66   $��
10,126,0,0q�6Q   $	��Top=�6e   $��2��6}   �� 5   
     dic_ProductsDescription#���  6   $
��Left=�6D   $��
10,284,0,0q�6_   $	��Top=�6s   $��2��6�   �� 5   
   -   5         ��Name$ ProductsPhoto��5      $
��Left=�6'   $	��100��6B   $��
59,166,0,0q�6O   $	��Top=�6c   $	��100��6{   $��1��6�   �� 5   
   -   5         ��Name$
 name��5   ;     DefaultTextBox#���  6   $
��Left=�6I   $��	53,18,0,0q�6e    �� TextWrapping$
 Wrap=�6x   $	��Top=�6�   $	��120��6�   $��1��6�   �� 5   
   -   5        $ price��5   ;   #���  6   $
��Left=�6J   $��	53,43,0,0q�6e   $
 Wrap=�6x   $	��Top=�6�   $	��120��6�   $��1��6�   �� 5   
   -   5         ��Name$ rating��5      $
��Left=�6!   $��	53,73,0,0q�6<   $	��Top=�6O   $	��120��6g   $��20��6s   $��1��6   �� 5   
   -   5         ��Name$ typeOfProduct��5       �� SelectedValuePath$ Content.Text��6*   $��25��6K   $��
53,98,26,0q�6W   $	��Top=�6k   $��1��6�   .@�5      �� 	 �� 
IsSelected$
	 True��6   $��Фрукты��6-   �� 5      $
	 True��6   $��
Овощи��6-   �� 5      $
	 True��6   $'��!Молочные продукты��6-   5      �� 5   
   -   5        
 ��Name$
 selectPhoto��5   9     DefaultButton#���  6    	 dic_SelectPhoto#��� 	 6N   $
��Left=�6z   $��
53,126,0,0q�6�   $	��Top=�6�   $	��120��6�   $��26��6�   $��12(�6�    �� IsCancel$
 True��6�   $��1��6  �� 5   
   -   5        $ description��5   ;   #���  6   $��20,333,20,55q�6P   $
 Wrap=�6f   $	��200��6z   $��97��6�   $��2��6�   �� 5   
    
 dic_ProductsTypeOfProduct#��� 
 6   $
��Left=�6F   $��	10,97,0,0q�6a   $	��Top=�6t   �� 5    
   -   5        $
 
addProduct��5    9   #���  6   $!��Добавить товар��6M   $
��Left=�6f   $��
26,434,0,0q�6�   $	��Top=�6�   $	��188��6�   $��26��6�   $��12(�6�   $
 True��6�   $��2��6�   5!      5"      