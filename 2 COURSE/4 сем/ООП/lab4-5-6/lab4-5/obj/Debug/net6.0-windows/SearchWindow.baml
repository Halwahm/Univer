   M S B A M L   `   `   `  ����A  =lab4-5, Version=1.0.0.0, Culture=neutral, PublicKeyToken=nullclr-namespace:lab4_5lab4_5  5   	       lab4_5.SearchWindow   5   	   W SPresentationCore, Version=6.0.2.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=6.0.2.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35e aSystem.Windows.Controls.Ribbon, Version=6.0.2.0, Culture=neutral, PublicKeyToken=b77a5c561934e089R NWindowsBase, Version=6.0.2.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35F 9http://schemas.microsoft.com/winfx/2006/xaml/presentation     5   	   R NSystem.Xaml, Version=6.0.2.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   &localclr-namespace:lab4_5     5   	   _ [MaterialDesignThemes.Wpf, Version=4.7.1.0, Culture=neutral, PublicKeyToken=df2a72020bd7962aFmaterialDesign1http://materialdesigninxaml.net/winfx/xaml/themes  5   	     � Title$  SearchWindow��5	   	   $	��320��6   $	��320��6+    � 
ResizeMode$ NoResize=�67   .��5
      �    DefaultGrid#���   6   .+�5   
   ��   dic_SearchLabelName#���  6   $
��Left=�6@   $��	10,10,0,0q�6[   $	��Top=�6n   �� 5   
   -   5         ��Name$
 name��5   ;     DefaultTextBox#���  6   $
��Left=�6I   $��	10,46,0,0q�6d    �� TextWrapping$
 Wrap=�6w   $	��Top=�6�   $	��150��6�   �� 5   
   -   5         ��Name$ SearchByName��5   9     DefaultButton#���  6     dic_SearchButton#���  6O   $
��Left=�6|   $��
186,42,0,0q�6�   $	��Top=�6�   6�   �� 5   
     dic_SearchLabelPrice#���  6   $
��Left=�6M   $��	10,79,0,0q�6h   $	��Top=�6{   �� 5   
   -   5         ��Name$ price��5      $
��Left=�6    $��
10,114,0,0q�6;   $	��Top=�6O   $	��150��6g    � Maximum$
 1000Q�6s   �� 5   
   -   5        $ SearchByPrice��5   9   #���  6   #���  6P   $
��Left=�6}   $��186,108,0,0q�6�   $	��Top=�6�   6�   �� 5   
     dic_SearchLabelType#���  6   $
��Left=�6L   $��
10,145,0,0q�6g   $	��Top=�6{   �� 5   
   -   5         ��Name$ typeOfProduct��5       �� SelectedValuePath$ Content.Text��6*   $��25��6K   $��10,174,160,0q�6W   $	��Top=�6m   .@�5      �� 	 �� 
IsSelected$
	 True��6   $��Фрукты��6-   �� 5      $
	 True��6   $��
Овощи��6-   �� 5      $
	 True��6   $'��!Молочные продукты��6-   5      �� 5   
   -   5        $ SearchByTypeOfProduct��5   9   #���  6   #���  6X   $
��Left=�6�   $��186,174,0,0q�6�   $	��Top=�6�   6�   �� 5   
     dic_SearchLabelRating#���  6   $
��Left=�6N   $��
10,211,0,0q�6i   $	��Top=�6}   �� 5   
   -   5        $ rating��5   ;   #���  6   $
��Left=�6K   $��
10,240,0,0q�6f   $
 Wrap=�6z   $	��Top=�6�   $	��150��6�   �� 5   
   -   5        $ SearchByRating��5   9   #���  6   #���  6Q   $
��Left=�6~   $��186,243,0,0q�6�   $	��Top=�6�   6�   5      5      