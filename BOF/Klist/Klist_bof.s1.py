from typing import List, Tuple

from outflank_stage1.task.base_bof_task import BaseBOFTask
from outflank_stage1.task.enums import BOFArgumentEncoding


class KlistBOF(BaseBOFTask):
    def __init__(self):
        super().__init__("klist", base_binary_name="Klist")

        self.parser.description = (
            "Displays a list of currently cached Kerberos tickets."
        )

        self.parser.add_argument(
            "action",
            choices=["purge"],
            nargs="?",
            help="Optional purge.",
        )

    def _encode_arguments_bof(
        self, arguments: List[str]
    ) -> List[Tuple[BOFArgumentEncoding, str]]:
        parser_arguments = self.parser.parse_args(arguments)

        if parser_arguments.action == "purge":
            return [(BOFArgumentEncoding.WSTR, "purge")]

        return []
