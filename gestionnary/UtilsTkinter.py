import tkinter as tk
import PIL.Image as i
import PIL.ImageTk as tki

class widget:
    Frame = tk.Frame.__name__
    Label = tk.Label.__name__
    Button = tk.Button.__name__
    Entry = tk.Entry.__name__
    Canvas = tk.Canvas.__name__
    Widget = tk.Widget.__name__
    Scrollbar = tk.Scrollbar.__name__
    Text = tk.Text.__name__
    Image = "Image"
    
    @staticmethod
    def frame():
        f = tk.Frame()
    @staticmethod
    def widget():
        f = tk.Widget()

class display:
    column = "column"
    columnspan = "columnspan"
    row = "row"
    rowspan = "rowspan"
    sticky = "sticky"
    expand = tk.N+tk.S+tk.E+tk.W

class color:
    l_b = "light blue"
    d_b = "dark blue"
    blu = "blue"
    bla = "black"

class fen(tk.Tk):
    def __init__(self) -> None:
        super().__init__()
        self.configuration()
        
        self.after(
            10,
            lambda:self.__constructAndShow()
        )
        
        self.mainloop()
    
    def configuration(self):
        """
            Basic configuration method (overwrite if you want to change it):
                geometry = 700x500
                state = zoomed
                grid = 10x10
        """
        self.geometry("700x500")
        self.state('zoomed')
        grid(self, "10x10")
    
    def constructWidget(self):
        """
            Basic construction of widget method (overwrite if you want to change it):
                Void
        """
        self.widget = {}
    
    def __constructAndShow(self):
        self.constructWidget()
        self.constructedWidget = constructFromDict(self, self.widget)
        widgetsDisplay(self.constructedWidget)
    
    def clear(self, target:dict=None, path:list[str]=[]):
        """
            Clear method:
                Allow you to destroy targeted widget using the path to this widget
                If target is None: destroy the whole fen
                Destroy the target if it's reached, even if len(path) is still >0
                ! recursive method for destroying widget in frame
        """
        if not target:
            d = self.children.copy()
            for k in d.keys():
                self.children[k].destroy()
            return
        
        target = target[path.pop(0)]
        if isContainer(target[0]):
            if len(path)>0:
                target = target[2]
                self.clear(target, path)
            else:
                target[0].destroy()
        else:
            target[0].destroy()

def grid(fen:tk.Tk, newGrid:str=None) -> str|None:
    """
        Set grid to newGrid of the form = COLUMNxROW
        Return current value if None is given
    """
    if newGrid:
        for i in range(int(newGrid.split("x")[0])):
            fen.columnconfigure(i, weight=1)
        for i in range(int(newGrid.split("x")[1])):
            fen.rowconfigure(i, weight=1)
    else:
        return "x".join([str(x) for x in fen.grid_size()])

def constructFromDict(fen:tk.Tk|tk.Frame, widgets:dict) -> dict[str:tuple[tk.Widget, dict[str:str|int]]]:
    """
        Prend en param un dict de la forme :\n
        dict = {
            "name":(name_of_a_widget:str, configure_info:dict, dispaly_info:dict, optional(underWidget):dict)
        }
        underWidget is only needed when the widget is a frame, and then we create (recursively) all the widget for this frame
    """
    result = {}
    
    for k in widgets.keys():
        if widgets[k]:
            if widgets[k][0] == widget.Frame:
                frame = tk.Frame(fen, cnf=widgets[k][1])
                grid(frame, widgets[k][4])
                result[k] = (
                    frame,
                    widgets[k][2],
                    constructFromDict(frame, widgets[k][3])
                )
            elif widgets[k][0] == widget.Image:
                imagePath = widgets[k][1].get("Image", None)
                if imagePath!=None: widgets[k][1].pop("Image")
                canva = tk.Canvas(fen, widgets[k][1])
                
                if imagePath!=None:
                    img = i.open(imagePath)
                    img = tki.PhotoImage(img)
                    canva.create_image(0, 0, anchor=tk.NW, image=img)
                
                result[k] = (
                    canva,
                    widgets[k][2]
                )
            else:
                result[k] = (
                    tk.__dict__[widgets[k][0]](fen, cnf=widgets[k][1]),
                    widgets[k][2]
                )
    
    return result

def widgetsDisplay(widgets:dict[str:tuple[tk.Widget, dict[str:str|int]]]):
    """
        Prend en param un dict de la forme :\n
        dict = {
            "name_of_a_widget":(widget:tk.Widget, dispaly_info:dict, optional(underWidget):dict)
        }
        underWidget is only needed when the widget is a frame, and then we display (recursively) all the widget for this frame
        ! recursive method for displaying sub-widget
    """
    for k in widgets.keys():
        if issubclass(type(widgets[k][0]), tk.Frame):
            widgets[k][0].grid(cnf=widgets[k][1])
            widgetsDisplay(widgets[k][2])
        else:
            widgets[k][0].grid(cnf=widgets[k][1])

def isContainer(w:tk.Widget):
    """
        Return if a tk.widget has sub-widget or not (like a main fen or a Frame)
    """
    return isinstance(w, (tk.Tk, tk.Frame))

def gridParam(
    column:int=...,
    columnspan:int=...,
    row: int = ...,
    rowspan: int = ...,
    sticky: str = ...,
    expand: bool=True
) -> dict[str:object]:
    """
        Construct a dict for the cnf param of tk.grid method using the other arg of this method
        Expand is basically to True in order to fill the place we let to the widget
    """
    result = {}
    
    result[display.column] = column if column!=... else None
    result[display.columnspan] =columnspan if columnspan!=... else None
    result[display.row] = row if row!=... else None
    result[display.rowspan] = rowspan if rowspan!=... else None
    result[display.sticky] = sticky if sticky!=... else None
    if expand:
        result[display.sticky] = display.expand
    
    return result


if __name__ == "__main__":
    pass